match_ip_and_port(int *ipOne, int *ipArray, int sizeOf_ipArray)
{
	int curIPAddrIdx;
	int curOctetIdx;
	int ipArrayIndex;


	for (curIPAddrIdx = 0; curIPAddrIdx < sizeOf_ipArray; curIPAddrIdx++) {


		for (curOctetIdx = 0; curOctetIdx < NUM_IP_OCTETS + 1; curOctetIdx++) {


			ipArrayIndex =
				curIPAddrIdx * (NUM_IP_OCTETS + 1) + curOctetIdx;

			if (ipOne[curOctetIdx] != ipArray[ipArrayIndex]) {
				break;
			}
		}


		if (curOctetIdx == NUM_IP_OCTETS + 1) {
			return 1;
		}

	}

	return 0;
}
