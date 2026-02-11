makeGroup (std::vector<FallingAmoeba> &group,
                 std::vector<FallingAmoeba> &ghosts, int16_t x, int16_t y,
                 std::set<std::pair<int16_t, int16_t> > &visitedPositions,
                 Amoeba::Colour colour, bool initialAmoeba)
{

    if ( visitedPositions.end () ==
            visitedPositions.find (std::make_pair (x, y)) )
    {


        Amoeba *amoeba = getAmoebaAt (x, y);
        if ( 0 != amoeba && !amoeba->isDying () )
        {


            if ( initialAmoeba )
            {
                colour = amoeba->getColour ();
            }


            if ( amoeba->getColour () == Amoeba::ColourGhost )
            {
                FallingAmoeba ghost;
                ghost.amoeba = amoeba;
                ghost.x = x;
                ghost.y = y;
                ghosts.push_back (ghost);


                visitedPositions.insert (std::make_pair (x, y));
            }
            else if ( colour == amoeba->getColour () )
            {

                FallingAmoeba groupMember;
                groupMember.amoeba = amoeba;
                groupMember.x = x;
                groupMember.y = y;
                group.push_back (groupMember);


                visitedPositions.insert (std::make_pair (x, y));


                makeGroup (group, ghosts, x, y - 1, visitedPositions, colour, false);
                makeGroup (group, ghosts, x + 1, y, visitedPositions, colour, false);
                makeGroup (group, ghosts, x, y + 1, visitedPositions, colour, false);
                makeGroup (group, ghosts, x - 1, y, visitedPositions, colour, false);
            }
        }
    }
}
