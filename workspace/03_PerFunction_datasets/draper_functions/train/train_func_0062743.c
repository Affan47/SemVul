ghw_disp_range (union ghw_type *type, union ghw_range *rng)
{
  switch (rng->kind)
    {
    case ghdl_rtik_type_e8:
      printf ("%s %s %s", ghw_get_lit (type, rng->e8.left),
	      ghw_get_dir (rng->e8.dir), ghw_get_lit (type, rng->e8.right));
      break;
    case ghdl_rtik_type_i32:
    case ghdl_rtik_type_p32:
      printf (GHWLD" %s "GHWLD,
	      rng->i32.left, ghw_get_dir (rng->i32.dir), rng->i32.right);
      break;
    case ghdl_rtik_type_i64:
    case ghdl_rtik_type_p64:
      printf (GHWLLD" %s "GHWLLD,
	      rng->i64.left, ghw_get_dir (rng->i64.dir), rng->i64.right);
      break;
    case ghdl_rtik_type_f64:
      printf ("%g %s %g",
	      rng->f64.left, ghw_get_dir (rng->f64.dir), rng->f64.right);
      break;
    default:
      printf ("?(%d)", rng->kind);
    }
}
