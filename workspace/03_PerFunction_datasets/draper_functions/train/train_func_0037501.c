SortByScore(){


    bool inorder=false;
    while (!inorder){
        inorder=true;
        int i;
        for(i=se_PlayerNetIDs.Len()-2;i>=0;i--)
            if (se_PlayerNetIDs(i)->TotalScore() < se_PlayerNetIDs(i+1)->TotalScore() ){
                SwapPlayersNo(i,i+1);
                inorder=false;
            }
    }
}
