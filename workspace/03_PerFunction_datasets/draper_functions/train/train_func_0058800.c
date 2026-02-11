findAllAnts(const Location loc,const bool friendly ,const int distance ){

    bug << "starting all ants with " << distance << endl;

    queue<Location> locQ;
    std::vector<Location> foundAnts;

    updateIndex++;

    locQ.push(loc);

    grid[loc.row][loc.col].updateIndex = updateIndex;

    while (!locQ.empty()){

        Location currentLoc = locQ.front();
        locQ.pop();

        for(int d=0; d<NUMDIRECTIONS; d++){
            Location nLoc = getLocation(currentLoc,d);

            if (taxidistance(nLoc,loc) > distance)
            {
                continue;
            }

            if((grid[nLoc.row][nLoc.col].updateIndex != updateIndex) && !(grid[nLoc.row][nLoc.col].isWater)){

                if(friendly){
                    if(grid[nLoc.row][nLoc.col].ant == 0){
                        bug << "allants found" << nLoc.row << ", " << nLoc.col << endl;
                        foundAnts.push_back(nLoc);
                    }
                }
                else if(grid[nLoc.row][nLoc.col].ant > 0){
                    bug << "allants found2" << nLoc.row << ", " << nLoc.col << endl;
                    foundAnts.push_back(nLoc);
                }
                grid[nLoc.row][nLoc.col].updateIndex = updateIndex;
                locQ.push(nLoc);
            }
        }
    }

    return foundAnts;


}
