u_near_unity(cmplx u, int n)
{
     double nlgabsu = n * log(cabs(u));
     return (log(UNITY_THRESH) < nlgabsu && nlgabsu < -log(UNITY_THRESH));
}
