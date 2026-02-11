PushPicture( const PictureParams& pp )
{


    if (IsPictureAvail(pp.PictureNum()))
        return;


    EncPicture* pptr = new EncPicture(pp);

    m_pic_data.push_back(pptr);


    std::pair<unsigned int,unsigned int> temp_pair(pp.PictureNum() ,  m_pic_data.size()-1);
    m_pnum_map.insert(temp_pair);
}
