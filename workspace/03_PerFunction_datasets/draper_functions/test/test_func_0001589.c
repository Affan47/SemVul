DrawBlock(int j, int i)
{

    int U = 0, V = 0;
    int value = int(m_cost[j][i].SAD / (double(m_scale) / 250));
    GetPowerUV(value, U, V);
    DrawMvBlockUV(j, i, U, V);


    if (m_mode[j][i]==dirac::INTRA)
    {
        int yidx = (j*m_draw_params.MvYBlockY());
        int xidx = (i*m_draw_params.MvYBlockX());
        for (int ypx=0; ypx<m_draw_params.MvYBlockY(); ++ypx)
        {
            if ((yidx+ypx)>=m_picture.Data(Y_COMP).LengthY() ||
                (xidx+m_draw_params.MvYBlockX()-1)>= m_picture.Data(Y_COMP).LengthX())
                break;
            m_picture.Data(Y_COMP)[(j*m_draw_params.MvYBlockY())+ypx][(i*m_draw_params.MvYBlockX())] = 250;
            m_picture.Data(Y_COMP)[(j*m_draw_params.MvYBlockY())+ypx][(i*m_draw_params.MvYBlockX())+m_draw_params.MvYBlockX()-1] = 250;
        }

        for (int xpx=0; xpx<m_draw_params.MvYBlockX(); ++xpx)
        {
            if ((yidx+m_draw_params.MvYBlockY()-1)>=m_picture.Data(Y_COMP).LengthY() ||
                (xidx+xpx)>= m_picture.Data(Y_COMP).LengthX())
                break;
            m_picture.Data(Y_COMP)[(j*m_draw_params.MvYBlockY())][(i*m_draw_params.MvYBlockX())+xpx] = 250;
            m_picture.Data(Y_COMP)[(j*m_draw_params.MvYBlockY())+m_draw_params.MvYBlockY()-1][(i*m_draw_params.MvYBlockX())+xpx] = 250;
        }
    }
}
