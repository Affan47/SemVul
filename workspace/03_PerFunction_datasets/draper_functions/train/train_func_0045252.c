addressLessThanComparison(const QHostAddress& addr1,  const QHostAddress& addr2)
    {
        if (addr1.protocol() == QAbstractSocket::IPv4Protocol &&
            addr2.protocol() == QAbstractSocket::IPv4Protocol) {
            return addr1.toIPv4Address() < addr2.toIPv4Address();
        }

        if (addr1.protocol() == QAbstractSocket::IPv6Protocol &&
            addr2.protocol() == QAbstractSocket::IPv6Protocol) {
            const Q_IPV6ADDR ipv6addr1 = addr1.toIPv6Address();
            const Q_IPV6ADDR ipv6addr2 = addr2.toIPv6Address();
            for (int i=0; i < 16; ++i) {
                if (ipv6addr1[i] != ipv6addr2[i]) {
                    return ((ipv6addr1[i] & 0xff) - (ipv6addr2[i] & 0xff));
                }
            }
        }

        return false;
    }
