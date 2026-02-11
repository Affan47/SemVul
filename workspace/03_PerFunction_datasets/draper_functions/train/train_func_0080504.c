WriteFieldComponent( const PicArray& pic_data , int field_num, const CompSort& cs)
{
    if (!m_op_pic_ptr)
    {
        std::cerr<<std::endl<<"Can't open picture data file for writing";
        return false;
    }

    unsigned char *comp;
    int xl,yl;
    if (cs == Y_COMP)
    {
        xl = m_sparams.Xl();
        yl = m_sparams.Yl();
        comp = m_frame_store;
    }
    else
    {
        xl = m_sparams.ChromaWidth();
        yl = m_sparams.ChromaHeight();
        if (cs == U_COMP)
        {
            comp = m_frame_store + (m_sparams.Xl() * m_sparams.Yl());
        }
        else
        {
            comp = m_frame_store + (m_sparams.Xl() * m_sparams.Yl()) + (xl*yl);
        }
    }


    int start = 0;

    int skip = 0;

    int end = 0;

    bool top_field = m_sparams.TopFieldFirst() ? (!(field_num%2)) :
                    (field_num%2);

    bool write_to_file = (m_sparams.TopFieldFirst() && !top_field) ||
                         (!m_sparams.TopFieldFirst() && top_field);

    if (m_sparams.TopFieldFirst())
    {
        if (top_field)
        {
            start = 0;
            skip = 2 * xl * sizeof(char);
            end = -(xl*yl);
        }
        else
        {
            start = xl;
            skip = 2 * xl * sizeof(char);
            end = 0;
        }
    }
    else
    {
        if (!top_field)
        {
            start = xl;
            skip = 2 * xl * sizeof(char);
            end = -(xl*yl);
        }
        else
        {
            start = 0;
            skip = 2 * xl * sizeof(char);
            end = xl;
        }
    }

    unsigned char *tempc = comp + start;

    int field_yl = yl>>1;
    int field_xl = xl;
    for (int j=0 ; j<field_yl ;++j)
    {
        for (int i=0 ; i<field_xl ; ++i)
        {
            tempc[i] = (unsigned char) (pic_data[j][i]+128);
        }
        tempc += skip;
    }
    tempc += end;

    if (write_to_file)
    {
        m_op_pic_ptr->write((char*) comp,xl*yl);
        m_op_pic_ptr->flush();
        return true;
    }

    return false;
}
