_compare_track_sort_index(Track* trk1, Track* trk2) {
    ExtraTrackData *etr1 = trk1->userdata;
    ExtraTrackData *etr2 = trk2->userdata;
    g_return_val_if_fail (etr1 && etr2, 0);

    return etr1->sortindex - etr2->sortindex;
}
