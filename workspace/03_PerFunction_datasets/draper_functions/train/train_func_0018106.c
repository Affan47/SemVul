Fill(ValueType val)
{
    for (int c=0; c<3; ++c ){
        m_pic_data[c]->Fill(val);
	if (m_up_pic_data[c] != NULL )
	    delete m_up_pic_data[c];
    }
}
