dawson(float x)
{
  if (x > 0.2)
    {

    int n0 = 2*(int)((0.5/H)*x + 0.5);
    float xp = x - (float)n0*H;
    float e1 = exp((2*H)*xp);
    float e2 = e1*e1;
    float d1 = n0 + 1;
    float d2 = d1 - 2;
    float sum = 0;
    sum = dawson_constant0*(e1/d1 + 1/(d2*e1));
    d1 += 2;  d2 -= 2;  e1 *= e2;
    sum += dawson_constant1*(e1/d1 + 1/(d2*e1));
    d1 += 2;  d2 -= 2;  e1 *= e2;
    sum += dawson_constant2*(e1/d1 + 1/(d2*e1));
    d1 += 2;  d2 -= 2;  e1 *= e2;
    sum += dawson_constant3*(e1/d1 + 1/(d2*e1));
    d1 += 2;  d2 -= 2;  e1 *= e2;
    sum += dawson_constant4*(e1/d1 + 1/(d2*e1));
    d1 += 2;  d2 -= 2;  e1 *= e2;
    sum += dawson_constant5*(e1/d1 + 1/(d2*e1));
    return M_1_SQRTPI*exp(-xp*xp)*sum;
    }
  else
    {
    float x2 = x*x;
    return x*(1 - (2.0/3.0)*x2*(1 - .4*x2*(1 - (2.0/7.0)*x2)));
    }
}
