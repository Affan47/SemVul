set_ind(const int num_torsions,  const GridMapSetInfo *const info, const State state)
{
   Genotype temp_Gtype;
   Phenotype temp_Ptype;
   Quat q;
   int i;

   temp_Gtype = generate_Gtype(num_torsions, info);
   temp_Ptype = generate_Ptype(num_torsions, info);


   temp_Gtype.write(state.T.x, 0);
   temp_Gtype.write(state.T.y, 1);
   temp_Gtype.write(state.T.z, 2);

#ifdef DEBUG_QUAT
#ifdef DEBUG_QUAT_PRINT
    pr( logFile, "DEBUG_QUAT: set_ind()\n" );
    (void) fflush(logFile);
#endif

    assertQuatOK( q );
#endif

   temp_Gtype.write( q.x, 3);
   temp_Gtype.write( q.y, 4);
   temp_Gtype.write( q.z, 5);
   temp_Gtype.write( q.w, 6);

   for (i=0;i<state.ntor; i++) {
       temp_Gtype.write(state.tor[i], 7+i);
   };

   Individual temp(temp_Gtype, temp_Ptype);


   temp.mapping();

   return(temp);
}
