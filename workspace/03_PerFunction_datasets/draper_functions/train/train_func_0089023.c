DrucErreurOutFileMesure ( Mesure
                             )
     float                       Mesure;

{

  if ( DrucStructStat.FILE_ERROR == DRUC_ERROR_FILE
     )
  {
    fprintf ( DrucErrorFile ,
              "Mesure Effectuee :%.1f\n",
              Mesure
            );
  }
}
