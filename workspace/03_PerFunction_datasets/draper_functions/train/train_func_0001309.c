P_SpawnPuff
( fixed_t	x,
  fixed_t	y,
  fixed_t	z )
{
    mobj_t*	th;
    int t;

    t = P_Random();
    z += ((t - P_Random()) << 10);


    th = P_SpawnMobj(x, y, z, MT_STRIFEPUFF);


    if(attackrange == PLAYERMELEERANGE)
        P_SetMobjState(th, S_POW2_00);


}
