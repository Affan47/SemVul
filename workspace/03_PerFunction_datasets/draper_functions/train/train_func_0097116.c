UpdateVariance(float *prVariance, const float rSum, const float rSumAdd, const int nGames)
{

    if (!nGames || nGames == 1) {
        *prVariance = 0;
        return;
    } else {


        float rDelta = rSumAdd;
        float rMuNew = rSum / nGames;
        float rMuOld = (rSum - rDelta) / (nGames - 1);
        float rDeltaMu = rMuNew - rMuOld;

        *prVariance = *prVariance * (1.0f - 1.0f / (nGames - 1.0f)) + nGames * rDeltaMu * rDeltaMu;

        return;

    }

}
