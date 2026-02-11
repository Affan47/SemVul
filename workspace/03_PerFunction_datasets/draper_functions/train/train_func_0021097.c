pdf_initialize_ids(gx_device_pdf * pdev)
{
    gs_param_string nstr;

    pdev->next_id = pdev->FirstObjectNumber;


    param_string_from_string(nstr, "{Catalog}");
    pdf_create_named_dict(pdev, &nstr, &pdev->Catalog, 0L);


    param_string_from_string(nstr, "{DocInfo}");
    pdf_create_named_dict(pdev, &nstr, &pdev->Info, 0L);
    {
        char buf[PDF_MAX_PRODUCER];

        pdf_store_default_Producer(buf);
        cos_dict_put_c_key_string(pdev->Info, "/Producer", (byte *)buf,
                                  strlen(buf));
    }


    {
        struct tm tms;
        time_t t;
        char buf[1+2+4+2+2+2+2+2+1+2+1+2+1+1+1];
        int timeoffset;
        char timesign;

        time(&t);
        tms = *gmtime(&t);
        tms.tm_isdst = -1;
        timeoffset = (int)difftime(t, mktime(&tms));
        timesign = (timeoffset == 0 ? 'Z' : timeoffset < 0 ? '-' : '+');
        timeoffset = any_abs(timeoffset) / 60;
        tms = *localtime(&t);

        gs_sprintf(buf, "(D:%04d%02d%02d%02d%02d%02d%c%02d\'%02d\')",
            tms.tm_year + 1900, tms.tm_mon + 1, tms.tm_mday,
            tms.tm_hour, tms.tm_min, tms.tm_sec,
            timesign, timeoffset / 60, timeoffset % 60);

        cos_dict_put_c_key_string(pdev->Info, "/CreationDate", (byte *)buf,
                                  strlen(buf));
        cos_dict_put_c_key_string(pdev->Info, "/ModDate", (byte *)buf,
                                  strlen(buf));
    }


    pdf_create_named_dict(pdev, NULL, &pdev->Pages, 0L);
}
