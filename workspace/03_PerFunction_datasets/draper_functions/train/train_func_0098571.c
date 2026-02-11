maisdef (p_ma)
p_ma_t p_ma;
{
 as_cold(p_ma->ma_minlev <= MAXLIBLEV + 1,"maisdef: Bad ma_minlev value.");
 return (p_ma->ma_minlev < (MAXLIBLEV + 1));
}
