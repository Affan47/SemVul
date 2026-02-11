s_Timestep(eGrid *grid, REAL currentTime, REAL minTimestep)
{
#ifdef DEBUG
    grid->Check();
#endif


    for(int i=grid->gameObjects.Len()-1;i>=0;i--)
    {
        eGameObject * c = grid->gameObjects(i);
        TimestepThisWrapper( grid, currentTime, c, minTimestep );
    }

#ifdef DEBUG
    grid->Check();
#endif
}
