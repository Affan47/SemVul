eval(const Vector&point,const ParameterSignal&sig,Vector&out)
{
ParameterSignal s(sig);
int i= 0;
while(i<indim()&&!sig[i])
i++;
s.signalAfter(i);

Vector x(indim());
x.zeros();
A.multaVec(x,point);
x.mult(sqrt(2.0));

func->eval(x,s,out);

out.mult(multiplier);
}
