at2_check_sms_memory(PrivAT2data *privdata)
{
    long values[4];
    int pos;
    int ret;
    Octstr *search_cpms = NULL;


    if ((ret = at2_send_modem_command(privdata, "AT+CPMS?", 0, 0)) != 0) {
        debug("bb.smsc.at2.memory_check", 0, "failed to send mem select command to modem %d", ret);
        return -1;
    }

    search_cpms = octstr_create("+CPMS:");

    if ((pos = octstr_search(privdata->lines, search_cpms, 0)) != -1) {

        int index = 0;
        pos += 6;


        pos = octstr_search(privdata->lines, octstr_imm(","), pos) + 1;


        while (index < 4 && pos < octstr_len(privdata->lines) &&
               (pos = octstr_parse_long(&values[index], privdata->lines, pos, 10)) != -1) {
            ++pos;
            ++index;
            if (index == 2)

                pos = octstr_search(privdata->lines, octstr_imm(","), pos) + 1;
        }

        if (index < 4) {

            debug("bb.smsc.at2", 0, "AT2[%s]: couldn't parse all memory locations : %d:'%s'.",
                  octstr_get_cstr(privdata->name), index,
                  &(octstr_get_cstr(privdata->lines)[pos]));
            O_DESTROY(search_cpms);
            return -1;
        }

        privdata->sms_memory_usage = values[0];
        privdata->sms_memory_capacity = values[1];


        ret = 0;


        O_DESTROY(privdata->lines);

    } else {
        debug("bb.smsc.at2", 0, "AT2[%s]: no correct header for CPMS response.",
              octstr_get_cstr(privdata->name));


        ret = -1;
    }

    O_DESTROY(search_cpms);
    return ret;
}
