obj_shudders(obj)
struct obj *obj;
{
	int	zap_odds;

	if (obj->oclass == WAND_CLASS)
		zap_odds = 3;
	else if (obj->cursed)
		zap_odds = 3;
	else if (obj->blessed)
		zap_odds = 12;
	else
		zap_odds = 8;


	if(obj->quan > 4L) zap_odds /= 2;

	return((boolean)(! rn2(zap_odds)));
}
