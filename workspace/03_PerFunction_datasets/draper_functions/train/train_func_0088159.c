count_add(gpointer a, gpointer b)
{
gint i;
struct count_pak *c1=a, *c2=b;

g_assert(c1 != NULL);
g_assert(c2 != NULL);


g_assert(c1->size == c2->size);

for (i=c1->size ; i-- ; )
  *(c1->bins+i) += *(c2->bins+i);
}
