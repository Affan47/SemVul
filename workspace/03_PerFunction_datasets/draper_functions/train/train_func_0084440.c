hrz_kfree_skb (struct sk_buff * skb) {
  if (ATM_SKB(skb)->vcc->pop) {
    ATM_SKB(skb)->vcc->pop (ATM_SKB(skb)->vcc, skb);
  } else {
    dev_kfree_skb_any (skb);
  }
}
