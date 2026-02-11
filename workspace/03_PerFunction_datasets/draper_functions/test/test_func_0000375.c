generateCpp( FILE * fp)
{
    CbcHeuristicGreedyCover other;
    fprintf(fp, "0#include \"CbcHeuristicGreedy.hpp\"\n");
    fprintf(fp, "3  CbcHeuristicGreedyCover heuristicGreedyCover(*cbcModel);\n");
    CbcHeuristic::generateCpp(fp, "heuristicGreedyCover");
    if (algorithm_ != other.algorithm_)
        fprintf(fp, "3  heuristicGreedyCover.setAlgorithm(%d);\n", algorithm_);
    else
        fprintf(fp, "4  heuristicGreedyCover.setAlgorithm(%d);\n", algorithm_);
    if (numberTimes_ != other.numberTimes_)
        fprintf(fp, "3  heuristicGreedyCover.setNumberTimes(%d);\n", numberTimes_);
    else
        fprintf(fp, "4  heuristicGreedyCover.setNumberTimes(%d);\n", numberTimes_);
    fprintf(fp, "3  cbcModel->addHeuristic(&heuristicGreedyCover);\n");
}
