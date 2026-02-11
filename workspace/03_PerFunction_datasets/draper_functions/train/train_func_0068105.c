APar_TrackInfo(uint8_t &total_tracks, uint8_t &track_num, short &codec_atom) {
    uint8_t track_tally = 0;
    short iter = 0;

    while (parsedAtoms[iter].NextAtomNumber != 0) {

        if (memcmp(parsedAtoms[iter].AtomicName, "trak", 4) == 0 && parsedAtoms[iter].AtomicLevel == 2) {
            track_tally += 1;
            if (track_num == 0) {
                total_tracks += 1;

            }
            else if (track_num == track_tally) {

                short next_atom = parsedAtoms[iter].NextAtomNumber;
                while (parsedAtoms[next_atom].AtomicLevel > parsedAtoms[iter].AtomicLevel) {

                    if (strncmp(parsedAtoms[next_atom].AtomicName, "stsd", 4) == 0) {

                        codec_atom = parsedAtoms[next_atom].AtomicNumber;


                        return;
                    }
                    else {
                        next_atom = parsedAtoms[next_atom].NextAtomNumber;
                    }
                }
            }
        }
        iter = parsedAtoms[iter].NextAtomNumber;
    }
    return;
}
