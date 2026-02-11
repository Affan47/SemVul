logScore(float x)
{
    if(x < minScore)
    {
        minScore = x;
    }
    if(x > maxScore)
    {
        maxScore = x;
    }

    sumSoFar += x;
    numScores++;
}
