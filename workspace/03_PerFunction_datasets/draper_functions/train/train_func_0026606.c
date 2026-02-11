align_pos(const pos_t pos) {

    const known_pos_range realign_pr(get_realignment_range(pos, _stageman.get_stage_data()));

    for (unsigned s(0); s<_n_samples; ++s) {
        sample_info& sif(sample(s));
        read_segment_iter ri(sif.read_buff.get_pos_read_segment_iter(pos));
        for (read_segment_iter::ret_val r; true; ri.next()) {
            r=ri.get_ptr();
            if (NULL==r.first) break;
            read_segment& rseg(r.first->get_segment(r.second));
            if (_client_opt.is_realign_submapped_reads ||
                rseg.is_treated_as_anytier_mapping()) {
                try {
                    realign_and_score_read(_client_opt,_client_dopt,sif.sample_opt,_ref,realign_pr,rseg,sif.indel_sync());
                } catch (...) {
                    log_os << "ERROR: Exception caught in align_pos() while realigning segment: "
                           << static_cast<int>(r.second) << " of read: " << (*r.first) << "\n";
                    throw;
                }

                if (rseg.is_realigned) {
                    if (! _stageman.is_new_pos_value_valid(rseg.realignment.pos,STAGE::POST_ALIGN)) {
                        log_os << "WARNING: read realigned outside bounds of realignment stage buffer. Skipping...\n"
                               << "\tread: " << rseg.key() << "\n";
                        rseg.is_invalid_realignment=true;
                    }
                }
            }
        }

#ifdef ESTDEPTH_DUMP
        if (sif.estdepth_buff.val(pos)>0) {
            log_os << "ESTDEPTH: pos,val: " << pos << " " << sif.estdepth_buff.val(pos) << "\n";
        }
#endif
    }
}
