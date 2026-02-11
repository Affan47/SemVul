handle() {
    if (transfer_wait) {
        transfer_wait = false;
        if (present_on_host) {
            if (log_actions) {
                printf("%s: starting upload of %s\n",
                    now_str(), physical_file_name
                );
            }
            chunk->parent->dfile->upload_rate.sample_inc(
                host->transfer_rate,
                chunk->parent->dfile->collecting_stats(),
                sim.now
            );
        } else {
            if (log_actions) {
                printf("%s: starting download of %s\n",
                    now_str(), physical_file_name
                );
            }
            chunk->parent->dfile->download_rate.sample_inc(
                host->transfer_rate,
                chunk->parent->dfile->collecting_stats(),
                sim.now
            );
        }
        t = sim.now + chunk->size/host->transfer_rate;
        sim.insert(this);
        return;
    }
    transfer_in_progress = false;
    if (present_on_host) {

        if (log_actions) {
            printf("%s: upload of %s completed\n",
                now_str(), physical_file_name
            );
        }
        chunk->parent->dfile->upload_rate.sample_inc(
            -host->transfer_rate,
            chunk->parent->dfile->collecting_stats(),
            sim.now
        );
        chunk->upload_complete();
    } else {
        present_on_host = true;
        if (log_actions) {
            printf("%s: download of %s completed\n",
                now_str(), physical_file_name
            );
        }
        chunk->parent->dfile->download_rate.sample_inc(
            -host->transfer_rate,
            chunk->parent->dfile->collecting_stats(),
            sim.now
        );
        chunk->download_complete();
    }
}
