ufraw_invalidate_layer(ufraw_data *uf, UFRawPhase phase)
{
    for (; phase < ufraw_phases_num; phase++) {
        uf->Images[phase].valid = 0;
        uf->Images[phase].invalidate_event = TRUE;
    }
}
