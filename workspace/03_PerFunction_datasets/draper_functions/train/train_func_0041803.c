test_dir_measured_bw(void)
{
  measured_bw_line_t mbwl;
  int i;
  const char *lines_pass[] = {
    "node_id=$557365204145532d32353620696e73746561642e bw=1024\n",
    "node_id=$557365204145532d32353620696e73746561642e\t  bw=1024 \n",
    " node_id=$557365204145532d32353620696e73746561642e  bw=1024\n",
    "\tnoise\tnode_id=$557365204145532d32353620696e73746561642e  "
                "bw=1024 junk=007\n",
    "misc=junk node_id=$557365204145532d32353620696e73746561642e  "
                "bw=1024 junk=007\n",
    "end"
  };
  const char *lines_fail[] = {

    "node_id=None bw=1024\n",
    "node_id=$None bw=1024\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=None\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=1024.0\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=.1024\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=1.024\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=1024 bw=0\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=1024 bw=None\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=-1024\n",

    "node_i",
    "node_i\n",
    "node_id=",
    "node_id=\n",
    "node_id=$557365204145532d32353620696e73746561642e bw=",
    "node_id=$557365204145532d32353620696e73746561642e bw=1024",
    "node_id=$557365204145532d32353620696e73746561642e bw=\n",
    "node_id=$557365204145532d32353620696e7374",
    "node_id=$557365204145532d32353620696e7374\n",
    "",
    "\n",
    " \n ",
    " \n\n",

    " node_id= ",
    "node_id==$557365204145532d32353620696e73746561642e bw==1024\n",
    "node_id=$55736520414552d32353620696e73746561642e bw=1024\n",
    "node_id=557365204145532d32353620696e73746561642e bw=1024\n",
    "node_id= $557365204145532d32353620696e73746561642e bw=0.23\n",
    "end"
  };

  for (i = 0; strcmp(lines_fail[i], "end"); i++) {

    test_assert(measured_bw_line_parse(&mbwl, lines_fail[i]) == -1);
  }

  for (i = 0; strcmp(lines_pass[i], "end"); i++) {

    test_assert(measured_bw_line_parse(&mbwl, lines_pass[i]) == 0);
    test_assert(mbwl.bw == 1024);
    test_assert(strcmp(mbwl.node_hex,
                "557365204145532d32353620696e73746561642e") == 0);
  }

 done:
  return;
}
