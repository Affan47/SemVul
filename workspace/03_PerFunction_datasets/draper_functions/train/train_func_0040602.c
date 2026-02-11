combatMove(){

    state.bug << "combat movement" << endl;

    for(vector<Combat>::iterator itr = state.combats.begin();itr < state.combats.end(); itr++){

        Combat c = (*itr);

        if(state.grid[c.friendlyAnt.row][c.friendlyAnt.col].moved > 0){
            continue;
        }

        int moveToMake = -1;
        int dist = state.taxidistance(c.friendlyAnt,c.enemyAnt);
        for(int d=0; d<NUMDIRECTIONS; d++)
        {
            Location loc = state.getLocation(c.friendlyAnt, d);
            if(!state.grid[loc.row][loc.col].isWater && state.grid[loc.row][loc.col].ant != 0)
            {
                int newdist = state.taxidistance(loc,c.enemyAnt);
                state.bug << "friends" << c.numfriendlyinrangeofbad << "bad" << c.numenemiesinrangeofgood << endl;
                if( c.numfriendlyinrangeofbad > c.numenemiesinrangeofgood){
                    state.bug << "ATTACK" << endl;
                    if(newdist < dist  ) {
                        moveToMake = d;
                        dist = newdist;
                    }
                }else if( c.numfriendlyinrangeofbad <= c.numenemiesinrangeofgood){
                    state.bug << "RUNAWAY" << endl;
                    if(newdist > dist  ) {
                        moveToMake = d;
                        dist = newdist;
                    }
                }else{
                    state.bug << "STAY" << endl;
                    if(newdist == dist) {
                        moveToMake = d;
                        dist = newdist;
                    }
                }
            }
        }
        if (moveToMake != -1){
            state.makeMove(c.friendlyAnt, moveToMake);
        }else{
            state.bug << "no good combat move founnd" << endl;
        }
        if(moveToMake == -1 && c.numfriendlyinrangeofbad < c.numenemiesinrangeofgood){
            state.grid[c.friendlyAnt.row][c.friendlyAnt.col].moved= 1;
        }
    }

}
