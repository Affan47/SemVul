handle_vote_update(int vote_no, int yes, int no, int abstain,
                        int num_voters)
{
  struct voteinfo *vi;

  vi = voteinfo_queue_find(vote_no);
  fc_assert_ret_msg(NULL != vi,
                    "Got packet_vote_update for non-existant vote %d!",
                    vote_no);

  vi->yes = yes;
  vi->no = no;
  vi->abstain = abstain;
  vi->num_voters = num_voters;

  voteinfo_gui_update();
}
