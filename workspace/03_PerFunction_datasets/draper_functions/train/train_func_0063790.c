vecThreshMess(int argc, t_atom *argv)
{
    if (argc >= 4)
    {
    	m_thresh[chAlpha] = CLAMP(atom_getfloat(&argv[3]) * 255);
    }
    else if (argc == 3) m_thresh[3] = 0;
    else
    {
    	error("not enough threshold values");
    	return;
    }

    m_thresh[chRed] = CLAMP(atom_getfloat(&argv[0]) * 255);
    m_thresh[chGreen] = CLAMP(atom_getfloat(&argv[1]) * 255);
    m_thresh[chBlue] = CLAMP(atom_getfloat(&argv[2]) * 255);
    m_Y = CLAMP(atom_getfloat(&argv[0]) * 255);
    setPixModified();
}
