locate_sof_marker()
{
    locate_soi_marker();

    int c = process_markers();

    switch (c) {
    case M_SOF2:
        m_progressive_flag = JPGD_TRUE;
    case M_SOF0:
    case M_SOF1: {
        read_sof_marker();
        break;
    }
    case M_SOF9: {
        stop_decoding(JPGD_NO_ARITHMITIC_SUPPORT);
        break;
    }
    default: {
        stop_decoding(JPGD_UNSUPPORTED_MARKER);
        break;
    }
    }
}
