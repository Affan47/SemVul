predict(double , long nb1,long  nb2)
{

    long            m;
    double          q;
    double          TEMP;
    for (m = n_states-1; m >=0; m--) {
        q = prob[m][nb1] * prob[m][nb2] * exptteig[m];
        p += q;
        TEMP = eig[m];
        dp += TEMP * q;
        d2p += TEMP * TEMP * q;
    }
}
