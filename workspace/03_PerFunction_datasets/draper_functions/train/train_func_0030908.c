defenderMove(){
    vector<Location>::iterator it;

    for(it = state.defenders.begin();it < state.defenders.end(); it++){

        if(state.grid[it->row][it->col].moved > 0){
            continue;
        }

        int moveToMake = -1;
        for(int d=0; d<NUMDIRECTIONS; d++)
        {
            Location loc = state.getLocation((*it), d);
            if(!state.grid[loc.row][loc.col].isWater && state.grid[loc.row][loc.col].ant != 0)
            {
                Location move = (*it);
                if (moveToMake != -1){
                    Location move = state.getLocation((*it), moveToMake);
                }
                if(state.grid[loc.row][loc.col].defensepriority > state.grid[move.row][move.col].defensepriority) {

                    moveToMake = d;
                }
            }
        }
        if (moveToMake != -1){
            state.makeMove((*it), moveToMake, false);
        }else{
            state.grid[it->row][it->col].moved = 1;
        }
    }
}
