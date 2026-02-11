GeoIP_is_private_ipnum_v4( unsigned long ipnum )
{
    return ((ipnum >= 167772160U && ipnum <= 184549375U)
            || (ipnum >= 2851995648U && ipnum <= 2852061183U)
            || (ipnum >= 2886729728U && ipnum <= 2887778303U)
            || (ipnum >= 3232235520U && ipnum <= 3232301055U)
            || (ipnum >= 2130706432U && ipnum <= 2147483647U)) ? 1 : 0;
}
