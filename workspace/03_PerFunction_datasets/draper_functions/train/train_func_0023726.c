s_CopyIntoGrid()
{
#ifdef DEBUG
    static int maxw=20;
    if (sg_netPlayerWalls.Len()>maxw)
        con << "Many walls: " << (maxw=sg_netPlayerWalls.Len()) << '\n';
#endif

    for (int i=sg_netPlayerWalls.Len()-1;i>=0;i--){
        gNetPlayerWall *w=sg_netPlayerWalls(i);
        if (w->inGrid && w->griddedid<0 && se_GameTime()>w->gridding)
            w->real_CopyIntoGrid(w->cycle_->Grid());
    }
}
