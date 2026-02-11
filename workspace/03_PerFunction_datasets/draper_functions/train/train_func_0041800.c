selection(Population &solutions)
{
   Individual *next_generation;

#ifdef DEBUG
   (void)fprintf(logFile, "gs.cc/Individual *Genetic_Algorithm::selection(Population &solutions)\n");
#endif

   next_generation = new Individual[solutions.num_individuals()];

   set_worst(solutions);
   switch(s_mode)
   {
      case Proportional:
         selection_proportional(solutions, next_generation);
         break;
      case LinearRanking:
         selection_linear_ranking(solutions, next_generation);
         break;
      case Tournament:


         (void)fprintf(logFile,"gs.cc/Unimplemented Selection Method - using proportional\n");
         selection_proportional(solutions, next_generation);
         break;
      case Boltzmann:
         (void)fprintf(logFile,"gs.cc/Unimplemented Selection Method - using proportional\n");
         selection_proportional(solutions, next_generation);
         break;
      default:
         (void)fprintf(logFile,"gs.cc/Unknown Selection Mode!\n");
   }

   return(next_generation);
}
