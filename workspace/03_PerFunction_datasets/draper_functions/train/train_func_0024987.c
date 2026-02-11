stamp_to_time(uint64_t stamp, Timestamp &tv) const
{
    uint32_t sec = (uint32_t) (stamp >> 32);

    stamp = (stamp & 0xFFFFFFFFULL) * 1000000000;
    stamp += (stamp & 0x80000000ULL) << 1;
    uint32_t nsec = (uint32_t) (stamp >> 32);
    if (nsec >= 1000000000) {
	nsec -= 1000000000;
	sec += 1;
    }
    tv = Timestamp::make_nsec(sec, nsec);
}
