MakePicHierarchy(const PicArray& data ,
                                    OneDArray< PicArray* >& down_data)
{

    DownConverter mydcon;


    int scale_factor = 1;
    for (int i=1 ; i<=m_depth;++i)
    {

        scale_factor*=2;
        down_data[i] = new PicArray( data.LengthY()/scale_factor , data.LengthX()/scale_factor);
    }


    if (m_depth>0)
    {
        mydcon.DoDownConvert( data , *(down_data[1]) );

        for (int i=1 ; i<m_depth ; ++i)
            mydcon.DoDownConvert( *(down_data[i]) , *(down_data[i+1]) );

    }
}
