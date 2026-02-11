__ecereMethod___ecereNameSpace__ecere__gfx__QuantNode_AddColor(struct __ecereNameSpace__ecere__gfx__QuantNode * this, int r, int g, int b, struct __ecereNameSpace__ecere__sys__OldList * nodeList, int * nonZeroN2)
{
int size = this->maxR - this->minR + (unsigned char)1;
int mr = (this->maxR - this->minR) / (unsigned char)2;
int mg = (this->maxG - this->minG) / (unsigned char)2;
int mb = (this->maxB - this->minB) / (unsigned char)2;

this->e += (float)(float)(((r - mr) * (r - mr) + (g - mg) * (g - mg) + (b - mb) * (b - mb)) >> this->level);
if(size > (4))
{
int ri = (r - this->minR) / (size >> 1);
int gi = (g - this->minG) / (size >> 1);
int bi = (b - this->minB) / (size >> 1);
struct __ecereNameSpace__ecere__gfx__QuantNode * child = this->nodes[ri][gi][bi];

if(!child)
{
child = this->nodes[ri][gi][bi] = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gfx__QuantNode);
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(nodeList, child);
child->level = this->level + 1;
child->parent = this;
child->minR = (unsigned char)(this->minR + ri * (size >> 1));
child->maxR = (unsigned char)(child->minR + (size >> 1) - 1);
child->minG = (unsigned char)(this->minG + gi * (size >> 1));
child->maxG = (unsigned char)(child->minG + (size >> 1) - 1);
child->minB = (unsigned char)(this->minB + bi * (size >> 1));
child->maxB = (unsigned char)(child->minB + (size >> 1) - 1);
}
__ecereMethod___ecereNameSpace__ecere__gfx__QuantNode_AddColor(child, r, g, b, nodeList, nonZeroN2);
}
else
{
if(!this->n2)
(*nonZeroN2)++;
this->n2++;
this->sr += (float)r;
this->sg += (float)g;
this->sb += (float)b;
}
}
