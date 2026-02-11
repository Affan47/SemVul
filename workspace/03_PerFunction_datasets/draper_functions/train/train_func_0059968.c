ftom( double f )
{


    return (f > 0 ? (log(f/440.0) / LOGTWO) * 12.0 + 69 : -1500);
}
