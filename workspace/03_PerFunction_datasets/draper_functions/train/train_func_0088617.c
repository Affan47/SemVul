dataslot_matches(t_dataslot *ds1, t_dataslot *ds2,
    int nametoo)
{
    return ((!nametoo || ds1->ds_name == ds2->ds_name) &&
        ds1->ds_type == ds2->ds_type &&
            (ds1->ds_type != DT_ARRAY ||
                ds1->ds_arraytemplate == ds2->ds_arraytemplate));
}
