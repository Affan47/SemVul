getSimilarityScore(const QString &str1, const char* str2)
{
    CoMatrix cmTarget( str2 );
    int targetLen = qstrlen( str2 );
    CoMatrix cm( str1.toLatin1().constData() );
    int delta = qAbs( (int) str1.length() - targetLen );

    int score = ( (intersection(cm, cmTarget).worth() + 1) << 10 ) /
        ( reunion(cm, cmTarget).worth() + (delta << 1) + 1 );

    return score;
}
