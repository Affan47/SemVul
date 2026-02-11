id_lookup(char*first,char*last,int ilk)

{int l,h;
if(last==NULL)last=first+(l=(int)strlen(first));
else l=(int)(last-first);
#line 932 "common.w"
{char*p=first;
h= *p;while(++p<last)h=((h<<1)+ *p)%hash_size;
}
#line 942 "common.w"
{id_pointer p=hash[h];
while(p!=NULL&&!names_match(p,first,l,ilk))p=p->hash_link;
if(p==NULL)
#line 955 "common.w"
{p=id_ptr;
if(id_ptr++ >=id_table_end)overflow("identifier");
name_begin(p)=store_string(first,l);
if(program==cweave)init_id_name(p,ilk);
p->hash_link=hash[h];hash[h]=p;
}
#line 947 "common.w"
return p;
}
#line 922 "common.w"
}
