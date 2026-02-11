operator++()
{
if(!end_flag){
if(s.size()==2){
s.sym()[0]++;
s.sym()[1]--;
}else{
++(*subit);
if(subit->isEnd()){
delete subit;
delete subs;
s.sym()[0]++;
subs= new SymmetrySet(s,s.dimen()-s.sym()[0]);
subit= new symiterator(*subs);
}
}
if(s.sym()[0]==s.dimen()+1)
end_flag= true;
}
return*this;
}
