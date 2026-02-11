sho_obj_return_to_u(obj)
struct obj *obj;
{

    if (bhitpos.x != u.ux || bhitpos.y != u.uy) {
	int x = bhitpos.x - u.dx, y = bhitpos.y - u.dy;

	tmp_at(DISP_FLASH, obj_to_glyph(obj));
	while(x != u.ux || y != u.uy) {
	    tmp_at(x, y);
	    delay_output();
	    x -= u.dx; y -= u.dy;
	}
	tmp_at(DISP_END, 0);
    }
}
