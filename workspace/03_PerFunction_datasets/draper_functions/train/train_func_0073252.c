test_iptables_rule1(void)
{
	int err;


	err = __connman_iptables_append("nat", "POSTROUTING",
				"-s 10.10.1.0/24 -o eth0 -j MASQUERADE");

	err = __connman_iptables_commit("nat");
	g_assert(err == 0);

	assert_rule_exists("nat",
		"-A POSTROUTING -s 10.10.1.0/24 -o eth0 -j MASQUERADE");

	err = __connman_iptables_delete("nat", "POSTROUTING",
				"-s 10.10.1.0/24 -o eth0 -j MASQUERADE");

	err = __connman_iptables_commit("nat");
	g_assert(err == 0);

	assert_rule_not_exists("nat",
		"-A POSTROUTING -s 10.10.1.0/24 -o eth0 -j MASQUERADE");
}
