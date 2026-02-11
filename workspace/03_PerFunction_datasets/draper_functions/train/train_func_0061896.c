pos_arg (const char* arg_)
{
    trace("HexDump::pos_arg");

    switch(m_pos_arg_count) {
    case 0:
        m_in_fname = arg_;
        break;

    case 1:
    default:
        DL((ASSA::ASSAERR,"Error: unexpected argument '%s'\n", arg_));
        DL((ASSA::ASSAERR,"Try `assa-hexdump --help` for more information.\n"));
        Assure_exit (false);
    }
    m_pos_arg_count++;
}
