cli_xml_output_replace_brick_task_params (xmlTextWriterPtr writer, dict_t *dict,
                                          char *prefix)
{

        int             ret = -1;
        char            key[1024] = {0,};
        char            *brick = NULL;


        ret = xmlTextWriterStartElement (writer, (xmlChar *)"params");
        XML_RET_CHECK_AND_GOTO (ret, out);

        snprintf (key, sizeof (key), "%s.src-brick", prefix);
        ret = dict_get_str (dict, key, &brick);
        if (ret)
                goto out;
        ret = xmlTextWriterWriteFormatElement (writer, (xmlChar *)"srcBrick",
                                               "%s", brick);
        XML_RET_CHECK_AND_GOTO (ret, out);


        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.dst-brick", prefix);
        ret = dict_get_str (dict, key, &brick);
        if (ret)
                goto out;
        ret = xmlTextWriterWriteFormatElement (writer, (xmlChar *)"dstBrick",
                                               "%s", brick);
        XML_RET_CHECK_AND_GOTO (ret, out);


        ret = xmlTextWriterEndElement (writer);

out:
        gf_log ("cli", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
