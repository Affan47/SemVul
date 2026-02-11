zchar_get_metrics2(const gs_font_base * pbfont, const ref * pcnref,
                   double pwv[4])
{
    const ref *pfdict = &pfont_data(gs_font_parent(pbfont))->dict;
    ref *pmdict;

    if (dict_find_string(pfdict, "Metrics2", &pmdict) > 0) {
        ref *pmvalue;

        check_type_only(*pmdict, t_dictionary);
        check_dict_read(*pmdict);
        if (dict_find(pmdict, pcnref, &pmvalue) > 0) {
            check_read_type_only(*pmvalue, t_array);
            if (r_size(pmvalue) == 4) {
                int code = num_params(pmvalue->value.refs + 3, 4, pwv);

                return (code < 0 ? code : metricsSideBearingAndWidth);
            }
        }
    }
    return metricsNone;
}
