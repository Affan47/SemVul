pegged_average(vector<double>& v, double anchor) {
    int n=v.size();
    double weights=0,sum=0,w;
    int i;
    if (n==1) {
        return v[0];
    }
    for (i=0; i<n; i++) {
        w=(1.0/(0.1*anchor+fabs(anchor-v[i])));
        weights+=w;
        sum+=w*v[i];
    }
    return sum/weights;
}
