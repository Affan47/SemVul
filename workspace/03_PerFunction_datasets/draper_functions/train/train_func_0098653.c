AntiAliasFilter( PicArray& out_data, const PicArray& in_data ) const{


    for (int i = in_data.FirstX(); i <= in_data.LastX(); ++i)
    {
        out_data[in_data.FirstY()][i] = (3*in_data[in_data.FirstY()][i] +
                                  in_data[in_data.FirstY()+1][i] +2 )>>2;
    }

    for (int j = in_data.FirstY()+1; j < in_data.LastY(); ++j)
    {
        for (int i = in_data.FirstX(); i <= in_data.LastX(); ++i)
        {
            out_data[j][i] = (in_data[j-1][i] + 2*in_data[j][i] + in_data[j+1][i] + 2)>>2;
        }
    }

    for (int i = in_data.FirstX(); i <= in_data.LastX(); ++i)
    {
        out_data[in_data.LastY()][i] = (in_data[in_data.LastY()-1][i] +
                                 3*in_data[in_data.LastY()][i] + 2)>>2;
    }
}
