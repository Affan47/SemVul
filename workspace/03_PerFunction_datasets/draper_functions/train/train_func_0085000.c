explorePathingMove(){
    for(vector<Path>::iterator itr = state.explorers.begin();itr < state.explorers.end(); itr++){

        state.bug << "explore pathing from" << itr->start.row << " " << itr->start.col << endl;

        if(state.grid[itr->start.row][itr->start.col].moved > 0){
            state.explorers.erase(itr);
            continue;
        }
        if (itr->steps.size() <1){
            state.explorers.erase(itr);
            continue;
        }
        Location loc = state.getLocation(itr->start, *(itr->steps.begin()));
        if(!state.grid[loc.row][loc.col].isWater && state.grid[loc.row][loc.col].ant != 0 ){
            state.makeMove(itr->start, *(itr->steps.begin()), false);
            state.bug << "explorepathing from" << itr->start.row <<" " << itr->start.col << " moving " <<  *(itr->steps.begin()) << endl;

            if (itr->steps.size() <3){
                state.explorers.erase(itr);
            }
            else{
                Location newstart = state.getLocation(itr->start,*(itr->steps.begin()));
                itr->move(newstart);
                state.bug << "after moving " << *(itr->steps.begin()) << " " <<itr->start.row << " col " << itr->start.col << endl << endl;
            }
        }
        else{
            state.explorers.erase(itr);
        }
    }


}
