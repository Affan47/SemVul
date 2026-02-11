sb(C *q){I i=0;C c;for(;c=*q++,i||c!='{';)i+=(c=='(')-(c==')');R q;}
