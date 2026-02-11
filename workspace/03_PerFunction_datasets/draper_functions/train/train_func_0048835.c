DoSubpel( EncQueue& my_buffer,int pic_num )
{
    m_predparams = &(my_buffer.GetPicture(pic_num).GetMEData().GetPicPredParams() );


    int ref1,ref2;

    const PictureSort psort = my_buffer.GetPicture(pic_num).GetPparams().PicSort();

    if (psort.IsInter())
    {

        const vector<int>& refs = my_buffer.GetPicture(pic_num).GetPparams().Refs();

        int num_refs = refs.size();
        ref1 = refs[0];
        if (num_refs>1)
            ref2 = refs[1];
        else
            ref2 = ref1;

        const PicArray& pic_data = my_buffer.GetPicture(pic_num).DataForME(m_encparams.CombinedME());
        const PicArray& refup1_data = my_buffer.GetPicture(ref1).UpDataForME(m_encparams.CombinedME());
        const PicArray& refup2_data = my_buffer.GetPicture(ref2).UpDataForME(m_encparams.CombinedME());

	MEData& me_data = my_buffer.GetPicture(pic_num).GetMEData();


        MatchPic( pic_data , refup1_data , me_data ,1 );

        if (ref1 != ref2 )
            MatchPic( pic_data , refup2_data , me_data ,2 );

    }
}
