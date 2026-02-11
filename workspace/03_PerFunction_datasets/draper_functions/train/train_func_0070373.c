operator= (const qmcnpit&qpit)
{
qmcpit::operator= (qpit);
if(pnt)
delete pnt;
if(qpit.pnt)
pnt= new Vector(*(qpit.pnt));
else
pnt= NULL;
return*this;
}
