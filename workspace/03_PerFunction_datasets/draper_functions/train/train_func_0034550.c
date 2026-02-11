find_short_packed_object(int len, const unsigned char *match, unsigned char *sha1)
{
	struct packed_git *p;
	const unsigned char *found_sha1 = NULL;
	int found = 0;

	prepare_packed_git();
	for (p = packed_git; p && found < 2; p = p->next) {
		uint32_t num, last;
		uint32_t first = 0;
		open_pack_index(p);
		num = p->num_objects;
		last = num;
		while (first < last) {
			uint32_t mid = (first + last) / 2;
			const unsigned char *now;
			int cmp;

			now = nth_packed_object_sha1(p, mid);
			cmp = hashcmp(match, now);
			if (!cmp) {
				first = mid;
				break;
			}
			if (cmp > 0) {
				first = mid+1;
				continue;
			}
			last = mid;
		}
		if (first < num) {
			const unsigned char *now, *next;
		       now = nth_packed_object_sha1(p, first);
			if (match_sha(len, match, now)) {
				next = nth_packed_object_sha1(p, first+1);
			       if (!next|| !match_sha(len, match, next)) {

					if (!found) {
						found_sha1 = now;
						found++;
					}
					else if (hashcmp(found_sha1, now)) {
						found = 2;
						break;
					}
				}
				else {

					found = 2;
					break;
				}
			}
		}
	}
	if (found == 1)
		hashcpy(sha1, found_sha1);
	return found;
}
