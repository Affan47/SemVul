DB_InsertSMS(const gn_sms * const data, const gchar * const phone)
{
    GString *buf, *phnStr, *text;
    time_t rawtime;
    struct tm * timeinfo;
    int error, i;
    sqlite3_stmt *stmt;

    if (phone[0] == '\0')
        phnStr = g_string_new("");
    else {
        phnStr = g_string_sized_new(32);
        g_string_printf(phnStr, "'%s',", phone);
    }

    text = g_string_sized_new(480);
    g_string_append(text, strEscape((gchar *) data->user_data[0].u.text));

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    buf = g_string_sized_new(1024);
    g_string_printf(buf, "INSERT INTO inbox (\"number\", \"smsdate\", \"insertdate\",\
                         \"text\", %s \"processed\") VALUES ('%s', \
                         '%02d-%02d-%02d %02d:%02d:%02d',\
                         '%02d-%02d-%02d %02d:%02d:%02d', '%s', %s 0)",
            phone[0] != '\0' ? "\"phone\"," : "", data->remote.number,
            data->smsc_time.year, data->smsc_time.month,
            data->smsc_time.day, data->smsc_time.hour,
            data->smsc_time.minute, data->smsc_time.second,
            timeinfo->tm_year + 1900, timeinfo->tm_mon,
            timeinfo->tm_mday, timeinfo->tm_hour,
            timeinfo->tm_min, timeinfo->tm_sec,
            text->str, phnStr->str);

    g_string_free(text, TRUE);
    g_string_free(phnStr, TRUE);

    error = sqlite3_prepare_v2(ppDbInbox, buf->str, -1, &stmt, NULL);
    if (error != SQLITE_OK) {
        g_print(_("%d: Parsing query %s failed!"), __LINE__, buf->str);
        g_print(_("Error: %s"), sqlite3_errmsg(ppDbInbox));
        return SMSD_NOK;
    }


    for (i = 0; i < 6; i++) {
        error = sqlite3_step(stmt);
        if (error == SQLITE_DONE)
            break;

        sleep(1);
        sqlite3_reset(stmt);
    }

    if (error != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        g_print(_("%d: INSERT INTO inbox failed.\n"), __LINE__);
        g_print(_("Error %d: %s\n"), error, sqlite3_errmsg(ppDbInbox));
        g_print(_("Query: %s\n"), buf->str);
        g_string_free(buf, TRUE);
        return SMSD_NOK;
    }

    sqlite3_finalize(stmt);
    g_string_free(buf, TRUE);
    return SMSD_OK;
}
