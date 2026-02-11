glusterd_volset_help (dict_t *dict)
{
        int                     ret = -1;
        gf_boolean_t            xml_out = _gf_false;

        if (dict_get (dict, "help" ))
                xml_out = _gf_false;
        else if (dict_get (dict, "help-xml" ))
                xml_out = _gf_true;
        else
                goto out;

        ret = glusterd_get_volopt_content (xml_out);
 out:
        gf_log ("glusterd", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
