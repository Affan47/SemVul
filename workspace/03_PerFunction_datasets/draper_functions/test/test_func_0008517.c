__ecereMethod___ecereNameSpace__ecere__gfx3D__Matrix_Determinant(struct __ecereNameSpace__ecere__gfx3D__Matrix * this)
{
double result = 0, i = 1;
int n;

for(n = 0; n < 4; n++, i *= -1)
{
double det;
double msub3[3][3];
int di, dj;

for(di = 0; di < 3; di++)
{
for(dj = 0; dj < 3; dj++)
{
int si = di + ((di >= 0) ? 1 : 0);
int sj = dj + ((dj >= n) ? 1 : 0);

msub3[di][dj] = this->m[si][sj];
}
}
det = msub3[0][0] * (msub3[1][1] * msub3[2][2] - msub3[2][1] * msub3[1][2]) - msub3[0][1] * (msub3[1][0] * msub3[2][2] - msub3[2][0] * msub3[1][2]) + msub3[0][2] * (msub3[1][0] * msub3[2][1] - msub3[2][0] * msub3[1][1]);
result += this->m[0][n] * det * i;
}
return result;
}
